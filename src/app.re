[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

type action =
  | SetInputRef(Js.nullable(Dom.element))
  | AddTodo(string)
;

type state = {
  todos: list(string),
  inputRef: ref(option(Dom.element))
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { todos: [], inputRef: ref(None) },
  reducer: (action, state) =>
    switch action {
    | SetInputRef(r) =>
      let inputRef = ref(Js.Nullable.to_opt(r));
      ReasonReact.Update({ ...state, inputRef })
    | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ todo, ...state.todos ] })
    },
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <input _type="text" ref=((r) => self.send(SetInputRef(r))) />
      <p className="App-intro">
        (ReasonReact.arrayToElement(Array.of_list(List.rev(List.map(todo => {
          ReasonReact.stringToElement(todo)
        }, self.state.todos)))))
      </p>
    </div>
  }
};
