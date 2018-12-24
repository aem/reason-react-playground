type state = {
  todos: list(string),
  completed: list(string),
};

type action =
  | AddTodo(string)
  | CompleteTodo(string)
  | UncompleteTodo(string);

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {todos: [], completed: []},
  reducer: (action, state) =>
    switch (action) {
    | AddTodo(todo) =>
      ReasonReact.Update({...state, todos: [todo, ...state.todos]})
    | CompleteTodo(todo) =>
      ReasonReact.Update({
        completed: [
          List.find(el => el == todo, state.todos),
          ...state.completed,
        ],
        todos: List.filter(el => todo != el, state.todos),
      })
    | UncompleteTodo(todo) =>
      ReasonReact.Update({
        completed: List.filter(el => todo != el, state.completed),
        todos: [
          List.find(el => el == todo, state.completed),
          ...state.todos,
        ],
      })
    },
  render: self =>
    <div className="app">
      <TodoInput addTodo=(todo => self.send(AddTodo(todo))) />
      <TodoList
        todos=self.state.todos
        completed=self.state.completed
        markComplete=(todo => self.send(CompleteTodo(todo)))
        markIncomplete=(todo => self.send(UncompleteTodo(todo)))
      />
    </div>,
};
