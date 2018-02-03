type action =
 | SetInput(string)
 | AddTodo(string)
;

type state = {
  todos: list(string),
  inputValue: string
};

let name = "Todo";

let component = ReasonReact.statelessComponent(name);

let initialState = { inputValue: "", todos: [] };

let reducer = (action: action, state: state): state =>
  switch action {
    | SetInput(inputValue) => {
      ...state,
      inputValue
    }
    | AddTodo(todo) => {
        todos: [ todo, ...state.todos ],
        inputValue: ""
      }
  }
;

let make = (~send, ~state: state, _children) => {
  ...component,
  render: _self => {
    <div className="App">
      <input 
        _type="text"
        value=(state.inputValue)
        onChange=((evt) => send(SetInput(Util.getInputValueFromEvent(evt))))
      />
      <button onClick=((_evt) => send(AddTodo(state.inputValue)))>
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

