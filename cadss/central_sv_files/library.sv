module register
  #(parameter WIDTH=16)
  (input logic clock, reset, clear, en,
   input logic [WIDTH-1:0] D,
   output logic [WIDTH-1:0] Q);

  always_ff @(posedge clock, posedge reset) 
    if (reset) Q <= 'b0;
    else if (en) Q <= D;
    else if (clear) Q <= 'b0;

endmodule: register

module counter
  #(parameter WIDTH=8)
  (input  logic [WIDTH-1:0] D,
   input  logic             en, clear, load, clock, up,
   output logic [WIDTH-1:0] Q);
   
  always_ff @(posedge clock)
    if (clear)
      Q <= {WIDTH {1'b0}};
    else if (load)
      Q <= D;
    else if (en)
      if (up)
        Q <= Q + 1'b1;
      else
        Q <= Q - 1'b1;
        
endmodule : counter

// asserts done for one cycle after a certain number of cycles
module countUpTo
  #(parameter WIDTH=8)
  (input  logic [WIDTH-1:0] D, goal,
   input  logic             en, clear, load, clock, up,
   output logic             done);
  
  logic [WIDTH-1:0] Q;
  assign done = (Q == goal-1);

  always_ff @(posedge clock)
    if (clear)
      Q <= {WIDTH {1'b0}};
    else if (load)
      Q <= D;
    else if (en)
      if (up)
        Q <= Q + 1'b1;
      else
        Q <= Q - 1'b1;
        
endmodule : countUpTo

// asserts done for one cycle after a certain number of cycles
module countUpToAndStop
  #(parameter WIDTH=8)
  (input  logic [WIDTH-1:0] D, goal,
   input  logic             en, clear, load, clock, up,
   output logic             done);
  
  logic [WIDTH-1:0] Q;
  assign done = (Q == goal-1);

  always_ff @(posedge clock)
    if (clear)
      Q <= {WIDTH {1'b0}};
    else if (load)
      Q <= D;
    else if (en && ~done)
      if (up)
        Q <= Q + 1'b1;
      else
        Q <= Q - 1'b1;
        
endmodule : countUpToAndStop

/*
 *  Create a FIFO (First In First Out) buffer with flit
 *  interface and constraints
 *    - The buffer is initally empty
 *    - Reads are combinational, so data_out is valid unless empty is asserted
 *    - Removal from the queue is processed on the clock edge.
 *    - Writes are processed on the clock edge
 *    - If a write is pending while the buffer is full, do nothing
 *    - If a read is pending while the buffer is empty, do nothing
 *    - HEIGHT must be a power of 2
 */
module FIFO #(parameter WIDTH=32, HEIGHT=16) (
    input logic              clock, reset_n,
    input logic [WIDTH-1:0]  data_in,
    input logic              we, re, 
    output logic [WIDTH-1:0] data_out,
    output logic             full, empty);

    logic [HEIGHT-1:0][WIDTH-1:0] Q;
    logic [$clog2(HEIGHT)-1:0] putPtr, getPtr; // pointers wrap automatically
    logic [$clog2(HEIGHT)+1:0] count;

    logic reset;
    assign reset = ~reset_n;

    assign empty = (count == 0);
    assign full = (count == HEIGHT);
    assign data_out = empty ? 'b0 : Q[getPtr];

    always_ff @(posedge clock, posedge reset) begin
      if (reset) begin
        count <= 0;
        getPtr <= 0;
        putPtr <= 0;
      end
      else begin
        if (re && we) begin
          getPtr <= getPtr + 1;
          putPtr <= putPtr + 1;
          Q[getPtr] <= {WIDTH{1'b1}};
          Q[putPtr] <= data_in;
        end else if (re && (!empty)) begin // not empty
          getPtr <= getPtr + 1;
          count <= count - 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end
        else if (we && (!full)) begin // not full
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          count <= count + 1;
        end
      end
    end
endmodule : FIFO

module PISO 
  #(parameter WIDTH = 64, OUTWIDTH = 16)
  (input logic clock, reset_n, 
   input logic [WIDTH-1:0] data_in,
   input logic re, we, 
   output logic [OUTWIDTH-1:0] data_out);

  logic [WIDTH-1:0] Q;

  assign data_out = Q[WIDTH-1:WIDTH-OUTWIDTH];

  always_ff @(posedge clock, negedge reset_n) begin
    if (~reset_n) begin
      Q <= 'b0;
    end else if (re) begin 
      Q <= Q << OUTWIDTH;
    end else if (we) begin
      Q <= data_in;
    end
  end 
endmodule: PISO

module SIPO
  #(parameter WIDTH = 16, OUTWIDTH = 64)
  (input logic clock, reset_n, 
   input logic [WIDTH-1:0] data_in,
   input logic re, we, 
   output logic [OUTWIDTH-1:0] data_out);
  
  logic [OUTWIDTH-1:0] Q;

  assign data_out = Q;

  always_ff @(posedge clock, negedge reset_n) begin
    if (~reset_n) begin
      Q <= 'b0;
    end else if (re) begin 
      Q <= 'b0;
    end else if (we) begin
      Q <= (Q << WIDTH) | data_in;
    end
  end 
endmodule: SIPO

/*
 *  Create a FIFO (First In First Out) buffer with flit
 *  interface and constraints
 *    - The buffer is initally empty
 *    - Reads are combinational, so data_out is valid unless empty is asserted
 *    - Removal from the queue is processed on the clock edge.
 *    - Writes are processed on the clock edge
 *    - If a write is pending while the buffer is full, do nothing
 *    - If a read is pending while the buffer is empty, do nothing
 *    - HEIGHT must be a power of 2
 *    - When re is asserted will start to send packets for DATA_WIDTH/flit size +1 cycles, assuming flit size > 16 
 *    - When we is asserted will take in packets for DATA_WIDTH/flit size +1 cycles, assuming flit size > 16 
 */
module FIFO_PISO #(parameter WIDTH=32, HEIGHT=16, OUTWIDTH=8) (
    input logic              clock, reset_n,
    input logic [WIDTH-1:0]  data_in,
    input logic              we, re, 
    output logic [OUTWIDTH-1:0] data_out,
    output logic             full, empty);

    logic done;

    logic [HEIGHT-1:0][WIDTH-1:0] Q;
    logic [$clog2(HEIGHT)-1:0] putPtr, getPtr; // pointers wrap automatically
    logic [$clog2(HEIGHT):0] count;

    logic [OUTWIDTH-1:0] flitOut;

    logic reset;
    assign reset = ~reset_n;

    assign empty = (count == 0);
    assign full = (count == HEIGHT);

    countUpToAndStop #(.WIDTH(32)) sameTurn(.D('b0), .goal(8),
                             .en(1'b1), .clear(re), .load(1'b0), .clock(clock), 
                             .up(1'b1), .done(done));

    PISO #(.WIDTH(WIDTH-OUTWIDTH), .OUTWIDTH(OUTWIDTH)) dout(.clock, .reset_n, 
                                             .data_in(Q[getPtr][WIDTH-OUTWIDTH-1:0]),
                                             .re(~done), .we(re), 
                                             .data_out(flitOut));

    assign data_out = re ? Q[getPtr][WIDTH-1:WIDTH-OUTWIDTH] : flitOut;

    always_ff @(posedge clock, posedge reset) begin
      if (reset) begin
        count <= 0;
        getPtr <= 0;
        putPtr <= 0;
      end
      else begin
        if (re && we && (!empty) && (!full)) begin
          getPtr <= getPtr + 1;
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end else if (re && (!empty)) begin // not empty
          getPtr <= getPtr + 1;
          count <= count - 1;
          Q[getPtr] <= {WIDTH{1'b1}};
        end
        else if (we && (!full)) begin // not full
          Q[putPtr] <= data_in;
          putPtr <= putPtr + 1;
          count <= count + 1;
        end
      end
    end
    
endmodule : FIFO_PISO


