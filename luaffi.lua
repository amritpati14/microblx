

ffi = require("ffi")

function read_header(fname)
   local f = assert(io.open(fname, "r"))
   local contents = f:read("*all")
   f:close()
   return contents
end

ffi.cdef(read_header("u5c_defs.h"))