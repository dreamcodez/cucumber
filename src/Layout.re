type publishedAction =
  | Login(string) /* username */
  | Logout
;

type publishedState = {
  username: option(string),
};

type send = publishedAction => unit;

let publishedInitialState = { username: None };

let publishedReducer = (action: publishedAction, _state: publishedState): publishedState =>
  switch action {
    | Login(username) => {
      username: Some(username)
    }
    | Logout => {
      username: None
    }
  }
;

let name = "Layout";

let component = ReasonReact.statelessComponent(name);

let make = (~send: send, ~state: publishedState, children) => {
  ...component,
  render: _self => {
    <div className=(name)>
      (switch (state.username) {
        | Some(username) => <b>(Util.text("logged in as " ++ username))</b>
        | None => Util.text("")
      })
      <button onClick=((_evt) => send(Login("bob")))>(Util.text("Login"))</button>
      <button onClick=((_evt) => send(Logout))>(Util.text("Logout"))</button>
      (ReasonReact.arrayToElement(children))
    </div>
  }
};