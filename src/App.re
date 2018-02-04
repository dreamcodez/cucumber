type action =
  | LoginAction(string)
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
  didMount: (self) => {
    let watcherID = ReasonReact.Router.watchUrl(url => {
      switch (url.path) {
      | ["todos"] => self.send(LoginAction("jimbob"))
      }
    });
  },
/*      | _ => showNotFoundPage()*/
  render: (self) => {
    <div className=name>
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Layout>
        (switch (self.state.username) {
          | Some(username) =>
            <div>
              <b>(Util.text("logged in as " ++ username))</b>
              <button onClick=((_evt) => self.send(LogoutAction))>(Util.text("Logout"))</button>
            </div>
          | None =>
            <div>
              <button onClick=((_evt) => self.send(LoginAction("bob")))>(Util.text("Login"))</button>
            </div>
        })

        <Todo
          sendLocal=((todoAction) => self.send(TodoAction(todoAction)))
          state=self.state.todo
        />
      </Layout>
    </div>
  }
};