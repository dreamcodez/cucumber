type action =
 | AddTodo(string)
;

type state = {
  todos: list(string),
  inputRef: ref(option(Dom.element))
};

let name = "Todo";

let component = ReasonReact.statelessComponent(name);

let initialState = { inputRef: ref(None), todos: [] };

let addTodo = (state: state, send, _evt) => {
  let todo = Util.getElementObj(state.inputRef);
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
        ...state,
        todos: [ todo, ...state.todos ]
      }
  }
;

let make = (~send, ~state: state, ~handle, _children) => {
  ...component,
  render: self => {
    <div className="App">
      <input _type="text" ref=(handle(setInputRef)) />
      <button onClick=(addTodo(state, send))>
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

