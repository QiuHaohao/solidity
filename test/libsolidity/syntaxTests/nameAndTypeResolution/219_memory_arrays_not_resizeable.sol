contract C {
    function f() public {
        uint[] memory x;
        x.length = 2;
    }
}
// ----
// TypeError: (72-80): Memory arrays cannot be resized.
