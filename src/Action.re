type t =
  | LoginAction(string)
  | LogoutAction
  | TodoAction(Todo.publishedAction)
;