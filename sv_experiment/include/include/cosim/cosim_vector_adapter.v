// Vector inout port adapter, to connect inout port and enable in 
// design to associated ports on the cosim interface
(*internal_module*) module cosim_vector_adapter (inport, in_enable, outport, out_enable, inoutport );

 // VECTOR_WIDTH parameter specifies the bit VECTOR_WIDTH for the vector adaptor
 parameter VECTOR_WIDTH = 1;

 input [(VECTOR_WIDTH - 1):0] inport;
 input in_enable;

 output [(VECTOR_WIDTH - 1):0] outport;
 reg    [(VECTOR_WIDTH - 1):0] outport;

 output out_enable;
 reg    out_enable;

 inout  [(VECTOR_WIDTH - 1):0] inoutport;
 reg    [(VECTOR_WIDTH - 1):0] inoutport_reg;

 reg [(VECTOR_WIDTH - 1):0] out_latch;
 reg [(VECTOR_WIDTH - 1):0] in_latch;
 reg [(VECTOR_WIDTH - 1):0] zval; 


 integer i;
 integer infer;
 integer inout_enable;
 integer zcheck;


initial
begin
  for (i=0; i<VECTOR_WIDTH; i=i+1'd1)
    begin
      zval[i] = 1'bz;
    end
  outport = zval;
  out_enable = 1'b0;
  out_latch = zval;
  in_latch = zval;
  inoutport_reg = zval;
end

assign inoutport = inoutport_reg;

// inout passes HDL values to SystemC
always @(inoutport )
begin
   // First task: infer whether or not this side of the
   // design is driving the inoutport
   inout_enable = 0;
   infer = 0;
   zcheck = 1;

   // other side is not asserting enable line:
   if (in_enable == 1'b0)  begin
     for (i=0; i < VECTOR_WIDTH; i=i+1) begin
       // test if all elements of vector are at Z
       if (inoutport[i] !== 1'bz) 
          zcheck = 0;
     end // for
     if (zcheck == 1)
       // easy case : vector just changed to tristate
       inout_enable = 0;
     else 
       // easy case: other side is not driving and we are driving
       // pass current inoutport value through and assert enable
       inout_enable = 1;
   end // IF;
   // other side is asserting enable line
   else if (in_enable == 1'b1) begin
     if (inoutport === in_latch) 
       // resolved value on inout port matches value latched
       // as last value in from other side.
       // do not "reflect" value back to other side
       inout_enable = 0;  
     else  begin
        // values are colliding, possibly producing an X
        // set inout_enable so we drive a value to our cosim partner
        inout_enable = 1;   
        for (i=0; i < VECTOR_WIDTH; i=i+1) begin
          if (inoutport[i] === 1'bx) 
        // INFERENCE:
        // As we do not directly have the value being driven
        // from this side of the cosimulation, but we know IN and INOUT
        // resolve to X - we can infer what is happening below:
        infer = 1;
        end
     end
   end

   if (inout_enable == 1) begin
      // set enable line to indicate we are driving a value from this side
      out_enable <= 1;
      // if our cosim partner is not driving a value, too, then drive
      // our current inout signal value. Otherwise, drive our last-known-good
      // latched value rather than send back a "collided" X value
      if (in_enable == 1'b0)  begin
        // latch a new known-good value input from this side
        // and send over the current inout signal value
        out_latch <= inoutport;
        outport <= inoutport;
      end // if
      else
        // Here, an IN value is being received from our cosim partner
        // check for inference flag set:
        // If so, drive value in out_latch to opposite of 
        // what IN value is, as their collision must be creating the X we are seeing:
        if (infer == 1) 
          for (i=0;  i<VECTOR_WIDTH; i=i+1) begin
            if (inoutport[i] === 1'bx ) begin
              case(inport[i])
                 1'bz: begin outport[i] <= 1'bx; out_latch[i] <= 1'bx; end
                 1'b0: begin outport[i] <= 1'b1; out_latch[i] <= 1'b1; end
                 1'b1: begin outport[i] <= 1'b0; out_latch[i] <= 1'b0; end
                 // other side is driving X all on its own
                 // set our side to Z until the collision clears; 
                 // do not reflect the X back to the other side
                 // and leave our currently latched value alone
                 1'bx: outport[i] <= 1'bz;
              endcase
            end // if
            else begin 
              outport[i] <= inoutport[i];
            end 
          end // LOOP
        else
          // Drive our last-known-good latched value to the other side;
          // do not reflect an X value back
          outport <= out_latch;
   end //IF;
   else begin
      // change to Z seen on INOUT value line
      outport <= zval;
      out_latch <= zval;
      out_enable <= 0;
   end
 end

// IN port passes values from cosim partner to HDL
 always @( inport or in_enable )
 begin
   in_latch <= inport;
   // Based on the enable line from the other side, drive
   // the new value or tristate our output
   if (in_enable == 1)
      inoutport_reg <= inport;
   else
      inoutport_reg <= zval;
 end // always

endmodule


