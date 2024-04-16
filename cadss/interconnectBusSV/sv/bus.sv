`default_nettype none

module bus 
#(parameter NUM_PROC = 4,
  parameter TRANSFER_TIME = 100)
(
  input logic clk, rst_l,
  input logic [NUM_PROC-1:0] request,
  input logic [NUM_PROC-1:0][$clog2(NUM_PROC):0] request_dest,
  output logic processed_request,
  output logic [NUM_PROC-1:0] request_avail
);

  logic [$clog2(TRANSFER_TIME)-1:0] countdown;
  logic bus_held;
  logic [$clog2(NUM_PROC):0] bus_owner;
  genvar i; 

  // TODO replace this with synthesizable structure and nack when full
  logic [$clog2(NUM_PROC):0] request_queue [$];

  always_ff @(posedge clk, negedge rst_l) begin
    if (!rst_l) begin
      bus_held <= 0;
    end

    if (request) begin
      for (int i = 0; i < NUM_PROC; i++) begin // todo improve type
        if (request[i]) begin
          request_queue.push_back(request_dest[i]);
        end
      end
    end
    if (bus_held && countdown == 0) begin
      bus_held <= 0;
    end else if (bus_held) begin
      countdown <= countdown - 1;
    end else if (request_queue.size() != 0) begin
      bus_held <= 1'b1;
      bus_owner <= request_queue.pop_front();
      countdown <= TRANSFER_TIME;
    end
  end

  for (i = 0; i < NUM_PROC; i++) begin
    assign request_avail[i] = countdown == 0 && bus_owner == i && bus_held;
  end

endmodule: bus