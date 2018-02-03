[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

type action =
  | AddTodo(string)
;

type state = {
  todos: list(string)
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { todos: [] },
  reducer: (action, state) =>
    switch action {
    | AddTodo(todo) => ReasonReact.Update({ todos: [ ...state.todos, todo ] })
    },
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <p className="App-intro">
        (ReasonReact.arrayToElement(Array.of_list(List.map(todo => {
          ReasonReact.stringToElement(todo)
        }, self.state.todos))))
      </p>
    </div>
  }
};
