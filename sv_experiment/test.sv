//----------------------------------------------
// SystemVerilog File
//----------------------------------------------
module dpi_tb;

  export "DPI-C" function sv_method;
  import "DPI-C" context function void c_method();
  
  initial
  begin
    $display("Before calling C Method");
    c_method();
    $display("After calling C Method");
  end
  
  function void sv_method();
    $display("  [SV-Prog]  Hello World...!");
  endfunction
endmodule
