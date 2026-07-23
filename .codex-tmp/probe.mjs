import { FileBlob, PresentationFile } from "@oai/artifact-tool";
const p = await PresentationFile.importPptx(await FileBlob.load("C:/Users/Roman/AppData/Local/Temp/codex-presentations/manual-20260723/plan-prezy/tmp/template-starter.pptx"));
for (const id of ["sh/2pkjidgr", "sl/c8rhml"]) {
  const o = p.resolve(id);
  console.log(id, Object.getOwnPropertyNames(Object.getPrototypeOf(o)));
  console.log("own", Object.keys(o));
}
