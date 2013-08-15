
local ubx=require "ubx"
local ubx_utils = require("lua/ubx_utils")

function init(block)
   print("init")
   for k=1,5 do
      ubx.config_add(block, "xaoo"..tostring(k), "int32_t", 3)
   end

   return true
end

function start(block)
   print("start")
   for k=1,10 do
      ubx.port_add(block, "hoop"..tostring(k), "meta", "int32_t", 5, nil, 0, 0)
   end
   return true
end

function step(block) print("step") end

function stop(block)
   print("stop")
   print("rm'ing", ubx.port_rm(block, "hoop10"))
   print("rm'ing", ubx.port_rm(block, "hoop9"))
   print("rm'ing", ubx.port_rm(block, "hoop8"))
   print("rm'ing", ubx.port_rm(block, "hoop7"))

   for k=1,6 do
      print("rm'ing", ubx.port_rm(block, "hoop"..tostring(k)))
   end
end
function cleanup(block) print("cleanup") end
