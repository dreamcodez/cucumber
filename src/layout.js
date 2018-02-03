type publishedAction =
  | Login(string) /* username */
  | Logout
;

type publishedState = {
  username: option(string),
};

type send = publishedAction => unit;

let publishedInitialState = { username: None };

let publishedReducer = (action: publishedAction, state: publishedState): publishedState =>
  switch action {
    | Login(username) => {
      username: Some(username)
    }
    | Logout => {
      username: None
    }
  }
;

let name = "Layout";

let component = ReasonReact.statelessComponent(name);

let make = (~send: send, ~state: publishedState, _children) => {
  ...component,
  render: _self => {
    <div className=(name)>
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