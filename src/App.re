type action =
  | LoginAction(string) /* username */
  | LogoutAction
  | TodoAction(Todo.publishedAction)
;

type state = {
  username: option(string),
  todo: Todo.publishedState
};

[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

let name = "App";

let component = ReasonReact.reducerComponent(name);

let make = (_children) => {
  ...component,
  initialState: (): state => {
    username: None,
    todo: Todo.publishedInitialState
  },
  reducer: (action: action, state: state) => {
    ReasonReact.Update(switch action {
      | LoginAction(username) => {
        ...state,
        username: Some(username)
      }
      | LogoutAction => {
        ...state,
        username: None
      }
      | TodoAction(todoAction) => {
        { ...state, todo: Todo.publishedReducer(todoAction, state.todo) }
      }
    });
  },
  render: ({ send, state }) => {
    <div className=name>
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Layout>
        (switch (state.username) {
          | Some(username) =>
            <div>
              <b>(Util.text("logged in as " ++ username))</b>
              <button onClick=((_evt) => send(LogoutAction))>(Util.text("Logout"))</button>
            </div>
          | None =>
            <div>
              <button onClick=((_evt) => send(LoginAction("bob")))>(Util.text("Login"))</button>
            </div>
        })

        <Todo
          send=((todoAction) => send(TodoAction(todoAction)))
          state=state.todo
        />
      </Layout>
    </div>
  }
};