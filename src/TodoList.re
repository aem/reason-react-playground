let component = ReasonReact.statelessComponent("TodoList");

let make =
    (
      ~todos: list(string),
      ~completed: list(string),
      ~markComplete: string => unit,
      ~markIncomplete: string => unit,
      _children,
    ) => {
  ...component,
  render: _self => {
    let completedTodos =
      Array.map(
        todo =>
          <li key=todo>
            <label>
              <button
                className="checkbox completed"
                onClick=(_event => markIncomplete(todo))>
                (ReasonReact.string("Mark Complete"))
              </button>
              (ReasonReact.string(todo))
            </label>
          </li>,
        Array.of_list(completed),
      );
      let incompleteTodos = Array.map(
        todo =>
          <li key=todo>
            <label>
              <button
                className="checkbox"
                onClick=(_event => markComplete(todo))>
                (ReasonReact.string("Mark Complete"))
              </button>
              (ReasonReact.string(todo))
            </label>
          </li>,
        Array.of_list(todos),
      );
    <>
      <ul>
      (
        Array.length(incompleteTodos) > 0 ?
          ReasonReact.array(incompleteTodos) :
          ReasonReact.string("Wahoo! All done! 🎉")
      )
      </ul>
      <ul>
        (
          Array.length(completedTodos) > 0 || Array.length(incompleteTodos) == 0 ?
            ReasonReact.array(completedTodos) :
            ReasonReact.string("Let's get something done!")
        )
      </ul>
    </>;
  },
};
