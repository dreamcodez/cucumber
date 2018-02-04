type publishedAction =
 | SetInput(string)
 | AddTodo(string)
;

type todo = {
  id: int,
  description: string
};

type publishedState = {
  nextId: int,
  todos: list(todo),
  inputValue: string
};

type send = publishedAction => unit;

let publishedInitialState = { inputValue: "", todos: [], nextId: 1 };


let publishedReducer = (action: publishedAction, state: publishedState): publishedState =>
  switch action {
    | SetInput(inputValue) => {
      ...state,
      inputValue
    }
    | AddTodo(todoStr) => {
      let todo = {
        id: state.nextId,
        description: todoStr
      };
      {
        nextId: state.nextId + 1,
        todos: [ todo, ...state.todos ],
        inputValue: ""
      }
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
            <li key=(string_of_int(todo.id))>(ReasonReact.stringToElement(todo.description))</li>
          }, state.todos)))))
        </ul>
      </div>
    </div>
  }
};