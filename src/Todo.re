type publishedAction =
 | SetInput(string)
 | AddTodo(string)
;

type publishedState = {
  todos: list(string),
  inputValue: string
};

type send = publishedAction => unit;

let publishedInitialState = { inputValue: "", todos: [] };


let publishedReducer = (action: publishedAction, state: publishedState): publishedState =>
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

let name = "Todo";

let component = ReasonReact.statelessComponent(name);

let make = (~sendLocal: send, ~state: publishedState, _children) => {
  ...component,
  render: _self => {
    <div className=name>
      <input 
        _type="text"
        value=(state.inputValue)
        onChange=((evt) => sendLocal(SetInput(Util.getInputValueFromEvent(evt))))
      />
      <button onClick=((_evt) => sendLocal(AddTodo(state.inputValue)))>
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