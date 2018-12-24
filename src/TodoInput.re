type state = {inputValue: string};

type action =
  | Change(string)
  | CreateTodo(string);

let component = ReasonReact.reducerComponent("TodoInput");

let make = (~placeholder="Conquer the world", ~addTodo: string => unit, _children) => {
  ...component,
  initialState: () => {inputValue: ""},
  reducer: (action, _state) =>
    switch (action) {
    | Change(newValue) => ReasonReact.Update({inputValue: newValue})
    | CreateTodo(todo) => {
      addTodo(todo)
      ReasonReact.Update({inputValue: ""})
    }
    },
  render: self =>
    <input
      placeholder
      value=self.state.inputValue
      onChange=(
        event => self.send(Change(ReactEvent.Form.target(event)##value))
      )
      onKeyPress=(event => {
        let key = ReactEvent.Keyboard.key(event);
        if (key == "Enter") {
          self.send(CreateTodo(self.state.inputValue))
        }
      })
    />,
};
