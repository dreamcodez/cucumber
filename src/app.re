[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let raiseWhenNone = (optional, msg: string) => {
  switch (optional) {
    | None => raise(Failure(msg))
    | Some(optional) => optional
  };
};

type action =
  | AddTodo(string)
;

type state = {
  todos: list(string),
  inputRef: ref(option(Dom.element))
};

type self = ReasonReact.self (state,  ReasonReact.noRetainedProps,  action);

let addTodo = (self: self, _evt) => {
  let el = raiseWhenNone(self.state.inputRef^, "input element missing");
  let todo = ReactDOMRe.domElementToObj(el);
  self.send(AddTodo(todo##value));
};

let setInputRef = (el: Js.nullable(Dom.element), {ReasonReact.state}) => {
  state.inputRef := Js.Nullable.to_opt(el);
};
let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { todos: [], inputRef: ref(None) },
  reducer: (action, state) =>
    switch action {
      | AddTodo(todo) => ReasonReact.Update({ ...state, todos: [ todo, ...state.todos ] })
    },
  render: self => {
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <input _type="text" ref=(self.handle(setInputRef)) />
      <button onClick=(addTodo(self))>
          (ReasonReact.stringToElement("another one"))
      </button>
      <p className="App-intro">
        <ul>
          (ReasonReact.arrayToElement(Array.of_list(List.rev(List.map(todo => {
            <li>(ReasonReact.stringToElement(todo))</li>
          }, self.state.todos)))))
        </ul>
      </p>
    </div>
  }
};

