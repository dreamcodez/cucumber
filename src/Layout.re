let name = "Layout";

let component = ReasonReact.statelessComponent(name);

let make = (children) => {
  ...component,
  render: _self => {
    <div className=(name)>
      (ReasonReact.arrayToElement(children))
    </div>
  }
};