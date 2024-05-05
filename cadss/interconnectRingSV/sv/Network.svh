`ifndef ROUTER_H
  `define ROUTER_H

  `define NUMNODES 4
  `define DATA_WIDTH 256
  `define ID_SIZE 8
  `define QUEUE_DEPTH 4

  `define NULL_PKT {src: 4'd0, dest: 4'd0, data: 24'h00_00_00}
`endif