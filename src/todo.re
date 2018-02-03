
type action =
 | AddTodo(string)
;

type state = {
  todos: list(string),
  inputRef: Type.domRef
};

type self = ReasonReact.self (state,  ReasonReact.noRetainedProps,  Action.t);

let name = "Todo";

let addTodo = (self: self, send, _evt) => {
  let todo = Util.getElementObj(self.state.inputRef);
  let value = todo##value;
  if (value != "") {
    todo##value #= "";
    send(AddTodo(value));
  };
  ignore(todo##focus());
};
let setInputRef = (el: Js.nullable(Dom.element), {ReasonReact.state}) => {
  state.inputRef := Js.Nullable.to_opt(el);
};
let component = ReasonReact.statelessComponent(name);

let reducer = (action: Action.t, state: state) =>
  switch action {
    | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ todo, ...state.todos ] })
  }
;

let make = (~send, ~state, _children) => {
  ...component,
  render: self => {
    <div className="App">
      <input _type="text" ref=(self.handle(setInputRef)) />
      <button onClick=(addTodo(self, send))>
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

