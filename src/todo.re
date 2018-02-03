type action =
 | AddTodo(string)
;

type state = {
  todos: list(string)
};

type internalState = {
  inputRef: ref(option(Dom.element))
};

let name = "Todo";

let component = ReasonReact.reducerComponent(name);

let initialState = { todos: [] };

let addTodo = (internalState: internalState, send, _evt) => {
  let todo = Util.getElementObj(internalState.inputRef);
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

let reducer = (action: action, state: state): state =>
  switch action {
    | AddTodo(todo) => {
        todos: [ todo, ...state.todos ]
      }
  }
;

type noAction =
  | NoAction
  | Foo
;
let make = (~send, ~state: state, _children) => {
  ...component,
  initialState: (): internalState => { inputRef: ref(None) },
  reducer: (_action: noAction, _state: internalState) => ReasonReact.NoUpdate,
  render: self => {
    <div className="App">
      <input _type="text" ref=(self.handle(setInputRef)) />
      <button onClick=(addTodo(self.state, send))>
          (ReasonReact.stringToElement("another one"))
      </button>
      <div className="App-intro">
        <ul>
          (ReasonReact.arrayToElement(Array.of_list(List.rev(List.map(todo => {
            <li>(ReasonReact.stringToElement(todo))</li>
          }, state.todos)))))
        </ul>
      </div>
    </div>
  }
};

