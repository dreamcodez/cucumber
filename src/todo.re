
type action =
 | SetInputRef(option(Dom.node))
 | AddTodo(string)
;

type state = {
  todos: list(string),
  inputRef: Type.domRef
};

let component = ReasonReact.statelessComponent("Todo");

let addTodo = (state, send, _evt) => {
  let todo = Util.getElementObj(state.inputRef);
  let value = todo##value;
  if (value != "") {
    todo##value #= "";
    send(AddTodo(value));
  };
  ignore(todo##focus());
};

let setInputRef = (send, el: Js.nullable(Dom.element)) => {
  send(SetInputRef(Js.Nullable.to_opt(el)));
};

let reducer = (action: action, state: state) =>
  switch action {
    | SetInputRef(optionalDomNode) =>
      ReasonReact.Update({
        ...state,
        inputRef: optionalDomNode
      })
    | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ todo, ...state.todos ] })
  }
;

let make = (~send, ~state, _children) => {
  ...component,
  render: self => {
    <div className="App">
      <input _type="text" ref=(setInputRef(send)) />
      <button onClick=(addTodo(state, send))>
          (ReasonReact.stringToElement("another one"))
      </button>
      <p className="App-intro">
        <ul>
          (ReasonReact.arrayToElement(Array.of_list(List.rev(List.map(todo => {
            <li>(ReasonReact.stringToElement(todo))</li>
          }, state.todos)))))
        </ul>
      </p>
    </div>
  }
};

