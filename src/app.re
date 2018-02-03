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
    switch action {
      | TodoAction(todoAction) => {
        let newState = { ...state, todo: Todo.reducer(todoAction, state.todo) };
        switch todoAction {
          | SetInputRef(_el) => ReasonReact.SilentUpdate(newState)
          | _otherwise => ReasonReact.Update(newState)
        }
      }
    };
  },
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Todo send=((todoAction: Todo.action) => self.send(TodoAction(todoAction))) state=self.state.todo />
    </div>
  }
};