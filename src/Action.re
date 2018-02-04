type action =
  | SetUrl(ReasonReact.Router.url)
  | LoginAction(string)
  | LogoutAction
  | TodoAction(Todo.publishedAction)
;

type state = {
  url: ReasonReact.Router.url,
  username: option(string),
  todo: Todo.publishedState
};

let reducer = (action: action, state) => {
  switch action {
    | SetUrl(url) => {
      ...state,
      url
    }
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
  }
};