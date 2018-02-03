type action =
  | LayoutAction(Layout.publishedAction)
  | TodoAction(Todo.publishedAction)
;

type state = {
  foo: int,
  todo: Todo.publishedState,
  layout: Layout.publishedState
};

[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let name = "App";

let component = ReasonReact.reducerComponent(name);

let make = (_children) => {
  ...component,
  initialState: (): state => {
    foo: 1,
    todo: Todo.publishedInitialState,
    layout: Layout.publishedInitialState
  },
  reducer: (action: action, state: state) => {
    ReasonReact.Update(switch action {
      | LayoutAction(layoutAction) => {
        { ...state, layout: Layout.publishedReducer(layoutAction, state.layout) }
      }
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
      <Layout
          send=((layoutAction) => self.send(LayoutAction(layoutAction)))
          state=self.state.layout
      >
        <Todo
          send=((todoAction) => self.send(TodoAction(todoAction)))
          state=self.state.todo
        />
      </Layout>
    </div>
  }
};