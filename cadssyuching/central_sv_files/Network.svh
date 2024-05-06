`ifndef ROUTER_H
  `define ROUTER_H

  `define DATA_WIDTH 512
  `define ID_SIZE 8
  `define QUEUE_DEPTH 4
  `define PKTBUFFERSIZE 4
  `define FLITSIZE 4

  `define NULL_PKT {src: 8'd0, dest: 8'd0, data: 24'h00_00_00}
`endif