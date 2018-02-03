let name = "App";

type state = {
  todos: list(string),
  inputRef: Type.domRef
};

type self = ReasonReact.self (state,  ReasonReact.noRetainedProps,  Action.t);

let addTodo = (self: self, _evt) => {
  let todo = Util.getElementObj(self.state.inputRef);
  let value = todo##value;
  if (value != "") {
    todo##value #= "";
    self.send(AddTodo(value));
  };
  ignore(todo##focus());
};
let setInputRef = (el: Js.nullable(Dom.element), {ReasonReact.state}) => {
  state.inputRef := Js.Nullable.to_opt(el);
};
let component = ReasonReact.reducerComponent(name);

let reducer = (action: Action.t, state: state) =>
  switch action {
    | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ todo, ...state.todos ] })
  }
;

let make = (_children) => {
  ...component,
  initialState: () => { todos: [], inputRef: ref(None) },
  reducer,
  render: self => {
    <div className="App">
      <input _type="text" ref=(self.handle(setInputRef)) />
      <button onClick=(addTodo(self))>
          (ReasonReact.stringToElement("another one"))
      </button>
      <p className="App-intro">
        <ul>
          (ReasonReact.arrayToElement(Array.of_list(List.rev(List.map(todo => {
            <li>(ReasonReact.stringToElement(todo))</li>
          }, self.state.todos)))))
        </ul>
      </p>
    </div>
  }
};

