open Action;

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
    ReasonReact.Update(reducer(action, state));
  },
  didMount: ({ send }) => {
    ReasonReact.SideEffects(_self => {
      ignore(ReasonReact.Router.watchUrl(url => {
        send(SetUrl(url))
      }));
    });
  },
  render: ({ send, state: state }) => {
    Js.log(state);
    <div className=name>
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
      </div>
      <Layout>
        (switch (state.username) {
          | Some(username) =>
            <div key="login">
              <b>(Util.text("logged in as " ++ username))</b>
              <button onClick=((_evt) => send(LogoutAction))>(Util.text("Logout"))</button>
            </div>
          | None =>
            <div key="login">
              <button onClick=((_evt) => send(LoginAction("bob")))>(Util.text("Login"))</button>
            </div>
        })

        <Todo
          key="todo"
          sendLocal=((todoAction) => send(TodoAction(todoAction)))
          state=state.todo
        />
      </Layout>
    </div>
  }
};