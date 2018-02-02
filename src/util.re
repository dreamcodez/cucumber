let common = (reactClass, props, ~commonProp1, ~commonProp2, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=Js.Obj.assign(props, {
      "commonProp1": commonProp1,
      "commonProp2": commonProp2
    }),
    children
  );