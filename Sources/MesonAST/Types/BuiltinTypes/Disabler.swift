public class Disabler: AbstractObject {
  public let name: String = "disabler"
  public var methods: [Method] = []
  public let parent: AbstractObject? = nil

  public init() { self.methods = [Method(name: "found", parent: self, returnTypes: [BoolType()])] }
}
