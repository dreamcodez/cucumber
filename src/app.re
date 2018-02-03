type action =
  | TodoAction(Todo.action)
;
type state = {
  todo: Todo.state
};

let name = "App";

[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let component = ReasonReact.reducerComponent(name);
let reducer = (action: action, state: state) =>
  switch action {
    | TodoAction(todoAction) => Todo.reducer(todoAction, state.todo)
  }
;

let make = (_children) => {
  ...component,
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Todo send=(self.send) state=(self.state.todo) />
    </div>
  }
};

