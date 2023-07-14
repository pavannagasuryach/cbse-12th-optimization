module helloworldfpga (
    input wire x,
    input wire y,
    input wire z,
    output wire F
);
always @(*)
begin
    F = (!x && !z) || (y && !z);
end
endmodule
