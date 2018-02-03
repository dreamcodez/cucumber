let raiseWhenNone = (optional, msg: string) => {
  switch (optional) {
    | None => raise(Failure(msg))
    | Some(optional) => optional
  };
};

let getElementObj = (domRef: Type.domRef) => {
  let el = raiseWhenNone(domRef^, "element missing from dom");
  ReactDOMRe.domElementToObj(el);
};

let common = (reactClass, props, ~commonProp1, ~commonProp2, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=Js.Obj.assign(props, {
      "commonProp1": commonProp1,
      "commonProp2": commonProp2
    }),
    children
  )
;

let getInputValueFromEvent = (event) =>
  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
;

let text = ReasonReact.stringToElement;
