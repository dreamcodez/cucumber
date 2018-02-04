type action =
  | LoginAction(string)
  | LogoutAction
  | TodoAction(Todo.publishedAction)
;

type state = {
  url: ReasonReact.Router.url,
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
    url: ReasonReact.Router.dangerouslyGetInitialUrl(),
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
  didMount: (_self) => {
    ReasonReact.SideEffects(self => {
      ignore(ReasonReact.Router.watchUrl(url => {
        switch (url.path) {
          | ["todos"] => self.send(LoginAction("jimbob"))
          | path => Js.log(path)
        }
      }));
    });
  },
  render: (self) => {
    Js.log([%obj self.state ]);
    <div className=name>
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Layout>
        (switch (self.state.username) {
          | Some(username) =>
            <div key="login">
              <b>(Util.text("logged in as " ++ username))</b>
              <button onClick=((_evt) => self.send(LogoutAction))>(Util.text("Logout"))</button>
            </div>
          | None =>
            <div key="login">
              <button onClick=((_evt) => self.send(LoginAction("bob")))>(Util.text("Login"))</button>
            </div>
        })

        <Todo
          key="todo"
          sendLocal=((todoAction) => self.send(TodoAction(todoAction)))
          state=self.state.todo
        />
      </Layout>
    </div>
  }
};