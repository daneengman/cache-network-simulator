module bus_tester ();
  localparam NUM_PROC = 4;
  
  logic clk, rst_l;
  logic [NUM_PROC-1:0] request;
  logic [NUM_PROC-1:0][$clog2(NUM_PROC):0] request_dest;
  logic processed_request;
  logic [NUM_PROC-1:0] request_avail;

  bus #(.NUM_PROC(NUM_PROC)) interconnect(.*);

  task clk_tick;
    clk <= 1;
    #5 clk <= 0;
    request <= '0;
    request_dest = '0;
    #5;
  endtask

  task reset;
    rst_l <= 0;
    rst_l = 1;
    request <= '0;
    request_dest = '0;
  endtask

  initial begin
    int count = 0;
    reset();
    request[0] <= 1;
    request_dest[0] <= 4;
    while (request_avail == 0) begin
      count++;
      if (count > 1000) begin
        $error("Timeout");
        $finish();
      end
    end
    $display("Success");
    $finish();
  end

endmodule: bus_tester