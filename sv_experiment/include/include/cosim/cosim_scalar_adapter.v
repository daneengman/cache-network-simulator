// Scalar inout port adapter, to connect inout port and enable in 
// design to associated ports on the cosim interface
(*internal_module*) module cosim_scalar_adapter (inport, in_enable, outport, out_enable, inoutport);
 
 input inport;
 input in_enable;

 output outport;
 reg    outport;

 output out_enable;
 reg    out_enable;

 inout  inoutport;
 reg    inoutport_reg;

 reg out_latch;
 reg in_latch;
 integer infer;
 integer inout_enable;

initial
begin
  outport = 1'bz;
  out_enable = 1'b0;
  out_latch = 1'bz;
  in_latch = 1'bz;
  inoutport_reg = 1'bz;
end

assign inoutport = inoutport_reg;

// inout passes HDL values to SystemC
always @(inoutport)
begin
     // First task: infer whether or not this side of the
     // design is driving the inoutport
     inout_enable = 0;
     infer = 0;

     // Cosim partner is not asserting enable line:
     if (in_enable == 1'b0)  begin
       if (inoutport === 1'bz)  begin
          // easy case : we just changed to tristate
          inout_enable = 0;
       end
       else 
          // easy case: Cosim partner is not driving and we are driving
          // pass current inoutport value thru and assert enable
          inout_enable = 1;   
     end
     // other side is asserting enable line
     else if (in_enable == 1'b1) begin
       if (inoutport === in_latch)  
          // resolved value on inout port matches value latched
          // as last value in from other side.
          // do not "reflect" value back to other side
          inout_enable = 0;  
       else begin
          // values are colliding, possibly producing an X
          // set inout_enable so we drive a value to our cosim parnter
          inout_enable = 1;   
          if (inoutport === 1'bx)
          // INFERENCE:
          // As we do not directly have the value being driven
          // from this side of the cosimulation, but we know IN and INOUT
          // resolve to X - we can infer what is happening below:
          infer = 1;
       end
     end

     if (inout_enable == 1) begin
        // set enable line to indicate we are driving a value from this side
        out_enable <= 1'b1;
        // if our cosim partner is not driving a value, too, then drive
        // our current inout signal value. Otherwise, drive our last-known-good
        // latched value rather than send back a "collided" X value
        if (in_enable == 1'b0)  begin
           // latch a new known-good value input from this side
           // and send over the current inout signal value
           out_latch <= inoutport;
           outport <= inoutport;
        end
        else 
           // Here, an IN value is being received from our cosim partner
           // check for inference flag set:
           // if so, drive value in out_latch to opposite of 
           // what IN value is, as their collision must be creating the X
           if (infer == 1)
             if (inoutport === 1'bx) begin
               case(inport)
                  1'bZ: begin outport <= 1'bX; out_latch <= 1'bX; end
                  1'b0: begin outport <= 1'b1; out_latch <= 1'b1; end
                  1'b1: begin outport <= 1'b0; out_latch <= 1'b0; end
                 // other side is driving X all on its own
                 // set our side to Z until the collision clears; 
                 // do not reflect the X back to the other side
                 // and leave our currently latched value alone
                  1'bx: outport <= 1'bz;
               endcase
             end
             else begin
                outport <= inoutport;
             end
           else
             // Drive our last-known-good latched value to the other side;
             // do not reflect an X value back
             outport <= out_latch;
     end
     else begin
        // change to Z seen on INOUT value line
        outport <= 1'bz;
        out_latch <= 1'bz;
        out_enable <= 1'b0;
     end
end


// in passes values from SystemC to HDL
always @(inport or in_enable)
begin
  // latch the new value for use in the process above
  in_latch <= inport;
  // Based on the enable line from the other side, drive
  // the new value or tristate our output
  if (in_enable == 1'b1) begin
    inoutport_reg <= inport;
    end
  else begin
    inoutport_reg <= 1'bz;
    end
end

endmodule

