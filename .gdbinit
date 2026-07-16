set pagination off
set print pretty on
set confirm off

define rerun
  shell make clean && make
  file ./bin/app
  break main
  run
end

document rerun
  Rebuild and start debugging from main()
end
