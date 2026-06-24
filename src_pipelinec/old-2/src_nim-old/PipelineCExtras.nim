#import std/macros
#macro `myStatic`*(
#  name: untyped
#): untyped =
#  pass
template `staticVar`*(name: untyped, T: typedesc): untyped =
  var name {.codegenDecl:"static $# $#".}: T
template `staticVarNoinit`*(name: untyped, T: typedesc): untyped =
  var name {.noinit,codegenDecl:"static $# $#".}: T
template `mkNonPtr`*(name: untyped, T: typedesc): untyped =
  var name {.noinit,codegenDecl:"$# $#".}: T

iterator `myRange`*(a, b: int): int = 
  var i = a
  {.emit:["for (;", i, " < ", b, "; ++", i, ") {"].}
  yield i
  {.emit:"}".}
iterator `myRange`*(a, b: uint): uint =
  var i = a
  {.emit:["for (;", i, " < ", b, "; ++", i, ") {"].}
  yield i
  {.emit:"}".}

#proc main() =
#  for x in crange(0, 10):
#    echo x
#main()
