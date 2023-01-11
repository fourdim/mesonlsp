import SwiftTreeSitter

public class DictionaryLiteral: Expression {
  public let file: MesonSourceFile
  public let values: [Node]
  public var types: [Type] = []

  init(file: MesonSourceFile, node: SwiftTreeSitter.Node) {
    self.file = file
    var bb: [Node] = []
    node.enumerateNamedChildren(block: { bb.append(from_tree(file: file, tree: $0)!) })
    self.values = bb
  }
  public func visit(visitor: CodeVisitor) { visitor.visitDictionaryLiteral(node: self) }
  public func visitChildren(visitor: CodeVisitor) {
    for arg in self.values { arg.visit(visitor: visitor) }
  }
}
