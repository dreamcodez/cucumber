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
        | Some(username) =>
          <div>
            <b>(Util.text("logged in as " ++ username))</b>
            <button onClick=((_evt) => send(Logout))>(Util.text("Logout"))</button>
          </div>
        | None =>
          <div>
            <button onClick=((_evt) => send(Login("bob")))>(Util.text("Login"))</button>
          </div>
      })
      (ReasonReact.arrayToElement(children))
    </div>
  }
};