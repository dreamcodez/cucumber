type action =
  | TodoAction(Todo.action)
;
type state = {
  foo: int,
  todo: Todo.state
};

[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let name = "App";

let component = ReasonReact.reducerComponent(name);

let make = (_children) => {
  ...component,
  initialState: _self => {
    foo: 1,
    todo: Todo.initialState
  },
  reducer: (action: action, state: state) => {
    let newState = switch action {
      | TodoAction(todoAction) => {
        { ...state, todo: Todo.reducer(todoAction, state.todo) }
      }
    };
    ReasonReact.Update(newState)
  },
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Todo
        send=((todoAction: Todo.action) => self.send(TodoAction(todoAction)))
        handle=(r => { todo: self.handle(r)})
        state=self.state.todo
        />
    </div>
  }
};