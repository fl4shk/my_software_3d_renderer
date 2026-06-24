import std/macros, std/strutils, std/tables

##macro cdecl*[T](
##  name: untyped,
##): untyped = 
##  result = newStmtList()
#
#  #result = newStmtList()
#  #for i in 0..<10:
#  #  let name = ident("myProc" & $i)
#  #  let content = newLit("I am procedure number #" & $i)
#
#  #  result.add quote do:
#  #    proc `name`() =
#  #      echo `content`
#
#template cif*(
#  expr: untyped,
#  stmtList: untyped
#): untyped =
#  let ret {.nodecl.} = expr
#  {.emit:"if (".}
#  {.emit:"ret".}
#  {.emit:") {\n".}
#  stmtList
#  {.emit:"}\n".}
#
##macro cif*(
##  expr: untyped,
##  stmtList: untyped,
##): untyped =
##  stmtList.expectKind nnkStmtList
##  let retName = ident("ret")
##  result = quote do:
##    {.emit:"if (".}
##    #cexpr(expr=`expr`)
##    #let temp {.nodecl.}: typeof(`expr`) = `expr`
##    #discard temp
##    #let `ret` = `expr`
##    let `retName` {.importc,nodecl.} = `expr`
##    #cexpr(expr=`expr`)
##    {.emit:") {\n".}
##    cstmtlist(stmtList=`stmtList`)
##    {.emit:"}\n".}
#
#macro celif*(
#  expr: untyped,
#  stmtList: untyped,
#): untyped =
#  result = quote do:
#    {.emit:"else if (".}
#    cexpr(expr=`expr`)
#    {.emit:") {\n".}
#    cstmtlist(stmtList=`stmtList`)
#    {.emit:"}\n".}
#
#macro celse*(
#  stmtList: untyped
#): untyped = 
#  result = quote do:
#    {.emit:"else {".}
#    cstmtlist(stmtList=`stmtList`)
#    {.emit:"}\n".}
#
#macro cstmtlist*(
#  stmtList: untyped
#): untyped =
#  stmtList.expectKind nnkStmtList
#
##macro cexpr*(
##  expr: untyped,
##): untyped =
##  result = quote do:
##    {.emit:"" & $`expr`.}
#template cexpr*(
#  expr: untyped
#): bool =
#  let temp {.nodecl.}: typeof(expr) = expr
#  temp
#
#
##macro `eq`*(
##  left: untyped,
##  right: untyped
##): untyped =
##  discard
#
##cif(3):
##  let a = 3
##  let b = 8

proc addIndent(res: var string, level: int) =
  ## Add indent (only if its needed).
  var
    idx = res.len - 1
    spaces = 0
  while res[idx] == ' ':
    dec idx
    inc spaces
  if spaces == 0 and res[idx] != '\n':
    res.add '\n'
  let level = level - spaces div 2
  for i in 0 ..< level:
    res.add "  "


proc addSmart(res: var string, c: char, others = {'}'}) =
  ## Ads a char but first checks if its already here.
  var idx = res.len - 1
  while res[idx] in Whitespace:
    dec idx
  if res[idx] != c and res[idx] notin others:
    res.add c

proc toCodeIfStmt(
  nodes: NimNode,
  res: var string,
  level = 0
) =
  for n in nodes:
    case n.kind:
    of nnkEmpty:
      discard
    of nnkElifBranch:
      discard
    of nnkElse:
      discard
    else:
      assert false

proc toCodeAsgn(
  nodes: NimNode,
  res: var string,
  level = 0
) =
  for n in nodes:
    case n.kind:
      else:
        assert false

proc toCodeTypeSection(
  nodes: NimNode,
  res: var string,
  level = 0,
) =
  discard

proc toCodeStmts(
  nodes: NimNode,
  res: var string,
  level: int
) = 
  for n in nodes:
    case n.kind:
    of nnkEmpty:
      discard
    of nnkSym:
      discard
    of nnkIfStmt:
      n.toCodeIfStmt(res=res, level=level + 1)
      #discard
    of nnkAsgn:
      n.toCodeAsgn(res=res, level=level + 1)
    #of nnkElifBranch:
    #  discard
    #of nnkElse:
    #  discard
    else:
      assert false
      

proc toCodeTopLevel(
  topLevelNode: NimNode,
  res: var string,
  level = 0
) = 
  assert topLevelNode.kind == nnkProcDef
  for n in topLevelNode:
    case n.kind:
    of nnkEmpty:
      discard
    of nnkSym:
      discard
    of nnkTypeSection:
      n.toCodeTypeSection(res, level + 1)
    #of nnkFormalParams:
    #  for param in n:
    else:
      n.toCodeStmts(res, level + 1)
      discard

proc toPipelineCInner*(
  s: NimNode,
): string =
  var code: string
  #code.add "asdf"
  var n = getImpl(s)

  var functions: Table[string, string]
  var globals: Table[string, string]

  for k, v in globals:
    code.add(v)
    code.add "\n"

  code.add "\n"
  for k, v in functions:
    code.add v
    code.add "\n"

  toCodeTopLevel(topLevelNode=n, res=code, level=0)

  return code

macro toPipelineC*(
  s: typed,
): string =
  newLit(toPipelineCInner(s))
