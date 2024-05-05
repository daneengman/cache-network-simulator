`default_nettype none

// typedef longint addr;


module bus 
#(parameter NUM_PROC = 4,
  parameter TRANSFER_TIME = 10)
(
  input logic clk, rst_l,
  input logic [NUM_PROC-1:0] request_in_avail,
  input  [NUM_PROC-1:0][47:0] addrs_in,
  input logic [NUM_PROC-1:0][$clog2(NUM_PROC):0] request_dest,
  output logic [NUM_PROC-1:0] processed_request,
  output logic [NUM_PROC-1:0] request_out_avail,
  output [NUM_PROC-1:0][47:0] addrs_out
);

  logic [$clog2(NUM_PROC)-1:0] first_priority;

  typedef struct packed {
    logic [$clog2(NUM_PROC)-1:0] src;
    logic [$clog2(NUM_PROC)-1:0] dest;
    // logic [511:0] data;
    logic [47:0] mem_address;
  } request_t;

  logic [$clog2(TRANSFER_TIME)-1:0] countdown;
  logic bus_held;
  genvar i; 

  // request_t request_queue [$];
  request_t request;

  always_ff @(posedge bus_held, negedge rst_l) begin
    if (~rst_l)
      first_priority <= 0;
    else
      if (first_priority == NUM_PROC - 1)
        first_priority <= 0;
      else
        first_priority <= first_priority + 1;
  end

  always_ff @(posedge clk, negedge rst_l) begin
    if (!rst_l) begin
      bus_held <= 0;
    end
    processed_request <= '0;

    // if (request_in_avail) begin
    //   for (int i = 0; i < NUM_PROC; i++) begin // todo improve type
    //     if (request_in_avail[i]) begin
    //       // $display("Request: %d", addrs_in[i]);
    //       request_queue.push_back({i,request_dest[i],addrs_in[i]});
    //     end
    //   end
    // end
    if (bus_held && countdown == 0) begin
      // $display("Request: %d", request.mem_address);
      bus_held <= 0;
    end else if (bus_held) begin
      countdown <= countdown - 1;
    end else if (request_in_avail) begin
      if (request_in_avail[first_priority]) begin
        request <= {first_priority,request_dest[first_priority],addrs_in[first_priority]};
        processed_request[first_priority] <= 1'b1;
      end else begin
        for (int i = 0; i < NUM_PROC; i++) begin // todo improve type
          if (request_in_avail[i]) begin
            // $display("Request: %d", addrs_in[i]);
            request <= {i,request_dest[i],addrs_in[i]};
            processed_request[i] <= 1'b1;
            break;
          end
        end
      end
      // request <= request_queue.pop_front();
      countdown <= TRANSFER_TIME;
      bus_held <= 1'b1;
    end
  end

  for (i = 0; i < NUM_PROC; i++) begin
    assign request_out_avail[i] = countdown == 0 && request.dest == i && bus_held;
    assign addrs_out[i] = (countdown == 0 && request.dest == i) ? request.mem_address : 0;
  end

endmodule: bus