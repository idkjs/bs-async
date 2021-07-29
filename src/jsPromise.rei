type exn +=
  pri
  | JSValue(Js.Types.tagged_t);

[@bs.send.pipe: Js.Promise.t('a)]
external map: ([@bs.uncurry] ('a => 'b)) => Js.Promise.t('b) = "then";
let recover: (exn => 'a, Js.Promise.t('a)) => Js.Promise.t('a);
let catch: (exn => Js.Promise.t('a), Js.Promise.t('a)) => Js.Promise.t('a);
let map_recover: ('a => 'b, exn => 'b, Js.Promise.t('a)) => Js.Promise.t('b);
let then_catch:
  ('a => Js.Promise.t('b), exn => Js.Promise.t('b), Js.Promise.t('a)) =>
  Js.Promise.t('b);
