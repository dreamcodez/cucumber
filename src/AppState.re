type action =
  | TodoAction(Todo.publishedAction)
;
type state = {
  foo: int,
  todo: Todo.publishedState
};

