public struct `BoolType`: Type {
  public let name: String = "bool"
  public var methods: [Method] = []

  public init() {
    self.methods = [
      Method(name: "to_int", parent: self, returnTypes: [LazyType(name: "int")]),
      Method(
        name: "to_string",
        parent: self,
        returnTypes: [LazyType(name: "str")],
        args: [
          PositionalArgument(name: "true_str", opt: true, types: [LazyType(name: "str")]),
          PositionalArgument(name: "false_str", opt: true, types: [LazyType(name: "str")]),
        ]
      ),
    ]
  }
  public func toString() -> String { return "bool" }
}
