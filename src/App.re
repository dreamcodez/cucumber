type action =
  | TodoAction(Todo.publishedAction)
;

type state = {
  foo: int,
  todo: Todo.publishedState
};

[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let name = "App";

let component = ReasonReact.reducerComponent(name);

let make = (_children) => {
  ...component,
  initialState: (): state => {
    foo: 1,
    todo: Todo.publishedInitialState
  },
  reducer: (action: action, state: state) => {
    ReasonReact.Update(switch action {
      | TodoAction(todoAction) => {
        { ...state, todo: Todo.publishedReducer(todoAction, state.todo) }
      }
    });
  },
  render: self => {
    <div className=name>
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Todo
        send=((todoAction) => self.send(TodoAction(todoAction)))
        state=self.state.todo
        />
    </div>
  }
};