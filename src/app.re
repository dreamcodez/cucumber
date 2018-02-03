[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

type action =
  | AddTodo(string)
;

type state = {
  todos: array(string)
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { todos: [] },
  reducer: (action, state) =>
    switch (action) {
    | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ ...todos, todo ] })
    },
  render: self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <p className="App-intro">
        List.map(todo => {
          <span>(todo)<span/>
        }, todos)
      </p>
    </div>
};
