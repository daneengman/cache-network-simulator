LIBRARY ieee;
USE ieee.std_logic_1164.all;

-- Scalar inout port handler, to connect inout port and enable lines
-- in the design to associated ports on the cosim interface.
ENTITY cosim_scalar_adapter_vhdl IS
 PORT ( inport    : IN std_logic := 'Z';
        in_enable : IN std_logic := '0';
        outport   : OUT std_logic := 'Z';
        out_enable: OUT std_logic := '0';
        inoutport : INOUT std_logic := 'Z');
END cosim_scalar_adapter_vhdl;

ARCHITECTURE behav OF cosim_scalar_adapter_vhdl IS
  SIGNAL out_latch : std_logic := 'Z';
  SIGNAL in_latch : std_logic := 'Z';
BEGIN
 -- OUT port passes HDL values to cosim partner
 PROCESS ( inoutport )
   VARIABLE inout_enable : std_logic := '0';
   VARIABLE infer : integer := 0;
   -- table used in reverse resolution inference logic
   TYPE reverse_res IS ARRAY (std_logic'LOW TO std_logic'HIGH) OF std_logic;
   CONSTANT  reverse_res_table : reverse_res := (
   --Value -- Index
      'U', -- 'U'
      'X', -- 'X'
      '1', -- '0'
      '0', -- '1'
      'Z', -- 'Z'
      'W', -- 'W'
      'H', -- 'L'
      'L', -- 'H'
      '-'  -- '-'
    );
BEGIN
   -- First task: infer whether or not this side of the
   -- design is driving the inoutport port
   inout_enable := '0';
   infer := 0;

   -- cosim partner is not asserting enable line:
   IF (in_enable = '0') THEN
      IF (inoutport = 'Z') THEN
       inout_enable := '0';
      ELSE
       -- port is driving from this side...
       -- assert enable so that cosim partner receives our value
       inout_enable := '1';
      END IF;
   -- cosim partner is asserting enable line
   ELSIF (in_enable = '1') THEN
     IF (inoutport = in_latch) THEN
       -- resolved value on inout port matches value latched
       -- as last value in from cosim partner.
       -- don't "reflect" value back to cosim partner
       inout_enable := '0';
     ELSE
        -- values are colliding, possibly producing an X
        -- set inout_enable so we drive a value to our cosim partner
        inout_enable := '1';
        IF (IS_X(inoutport)) THEN
          -- INFERENCE:
          -- As we don't directly have the value being driven
          -- from this side of the cosimulation, but we know IN and INOUT
          -- resolve to X - we can infer what's happening below:
          infer := 1;
        END IF;
     END IF;
   END IF;

   -- Now test to see what we should do
   IF (inout_enable = '1') THEN
      -- set enable line to indicate we're driving a value from this side
      out_enable <= '1';
      -- if our cosim partner is not driving a value, too, then drive
      -- our current inout signal value. Otherwise, drive our last-known-good
      -- latched value rather than send back a "collided" X value
      IF (in_enable = '0') THEN
        -- latch a new known-good value input from this side
        -- and send over the current inout signal value
        out_latch <= inoutport;
        outport <= inoutport;
      ELSE -- (in_enable = '1')
        -- Here, an IN value is being received from our cosim partner
        -- check for inference flag set:
        -- If so, drive value in out_latch to opposite of 
        -- what IN value is, as their collision must be creating the X we're seeing:
        IF (infer = 1) THEN
          IF (inoutport = 'X') THEN
            IF (NOT(IS_X(inport))) THEN   
              -- (0,1,H,L) values
              outport <= reverse_res_table(inport);
              out_latch <= reverse_res_table(inport);
            ELSIF (inport = 'Z') THEN
              outport <= 'X';
              out_latch <= 'X';
            ELSE
              -- cosim partner is driving (X, W, U, - ) all on its own
              -- set our side to Z until the collision clears;
              -- don't reflect the X back to the cosim partner 
              -- and leave our currently latched value alone
              outport <= 'Z';
            END IF;
          ELSE
              outport <= inoutport;
          END IF;
        ELSE
           outport <= out_latch;
        END IF;
      END IF;
   ELSE
      -- change to Z seen on INOUT value line
      outport <= 'Z';
      out_latch <= 'Z';
      out_enable <= '0';
   END IF;
 END PROCESS;

 -- IN port passes values from cosim partner to VHDL
 PROCESS ( inport, in_enable )
 BEGIN
   -- latch the new value for use in the process above
   in_latch <= inport;
   -- Based on the enable line from the cosim partner, drive
   -- the new value or tristate our output
   IF (in_enable = '1') THEN
      inoutport <= inport;
   ELSE
      inoutport <= 'Z';
   END IF;
 END PROCESS;
END behav;

