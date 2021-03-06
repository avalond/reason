/* don't auto-format this file until https://github.com/facebook/reason/issues/904 is resolved */

/* test setup dummy modules. These are here to make the transform pass the type checker. Also helps validating our transforms thanks to types */

module ReactDOMRe = {
  let createElement (tag, :props=?, children) = 1;
  let props (:className=?, :width=?, :comp=?, :compCallback=?, ()) = 1;
};
module Foo = {
  let make (:className=?, :width=?, :comp=?, :bar=?, children) = 1;
  let createElement (:className=?, :ref=?, :key=?, :width=?, :comp=?, :bar=?, :children, ()) = 1;
  module Bar = {
    let make (:className=?, children) = 1;
    let createElement (:className=?, :ref=?, :key=?, :children, ()) = 1;
  };
};
module Bar = {
  let make (:bar=?, children) = 1;
  let createElement (:bar=?, :children, ()) = 1;
};
module ReasonReact = {
  let element (:key=?, :ref=?, component) = 1;
};

/* ================ */

<div />;

<div className="hello" />;

<div className="hello" width="10" />;

<div className="hello" width="10"> (<li> <p/> </li>) (<Foo> <Bar /> </Foo>) </div>;

<div className="hello" comp=(<Foo bar=1 />)> <li /> <Foo bar=2 /> </div>;

<div className="hello" compCallback=(fun () => <Foo bar=1 />)> <li /> ((fun () => <Foo bar=2 />) ()) </div>;

/* ============== */

<Foo />;

<Foo className="hello" />;

<Foo className="hello" width="10" />;

<Foo className="hello" width="10"> (<li> <p/> </li>) (<Foo> <Bar /> </Foo>) </Foo>;

<Foo className="hello" comp=(<Bar bar=1 />)> <li /> <Bar bar=2 /> </Foo>;

/* ============== */

<Foo key="someKey" className="hello" />;

<Foo key=(Some("someKey")) ref=(Some(ref)) className="hello" />;

<Foo key=?(Some("someKey")) ref=?(Some(ref)) className="hello" />;

<Foo.Bar key="someKey" ref=(Some(ref)) className="hello"> <Bar /> </Foo.Bar>;

/* ============== */

/* Upcoming JSX syntax (pre-ppx) will desugar to Foo.make instad of
  Foo.createElement. Future-proof it in the ppx by transforming both to the
  correct ReasonReact-specific call */

([@JSX] Foo.make(:children [], ()));
