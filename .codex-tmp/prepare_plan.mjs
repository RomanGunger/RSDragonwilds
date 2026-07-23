import fs from "node:fs/promises";

const tmp = "C:/Users/Roman/AppData/Local/Temp/codex-presentations/manual-20260723/plan-prezy/tmp";
const rw = (shapeId, purpose) => ({ shapeId, action: "rewrite", purpose });
const rwp = (shapeId, purpose) => ({ shapeId, action: "rewrite-and-reposition", purpose });
const del = (shapeId, purpose) => ({ shapeId, action: "delete", purpose });

const map = {
  outputSlides: [
    {
      outputSlide: 1, sourceSlide: 1, narrativeRole: "opening thesis",
      reuseMode: "duplicate-slide",
      editTargets: [
        rw("sh/cvixczed", "conference title and date"),
        del("sh/nyd0z610", "empty inherited body placeholder"),
        del("sh/cj6tovah", "empty inherited body placeholder"),
        { shapeId: "im/4byhgn29", action: "fill-placeholder", purpose: "retain the existing media-themed visual as filled cover imagery" }
      ]
    },
    {
      outputSlide: 2, sourceSlide: 11, narrativeRole: "content overview",
      reuseMode: "duplicate-slide",
      editTargets: [
        rw("sh/6tovahoz", "slide title"),
        rw("sh/d4vmtwra", "theme groups one and two"),
        rwp("sh/sji5snel", "theme groups three and four"),
        rwp("sh/6hcrmhk3", "theme groups five and six"),
        rw("sh/3ylc7u54", "theme groups seven and eight")
      ]
    },
    {
      outputSlide: 3, sourceSlide: 11, narrativeRole: "speaker insights",
      reuseMode: "duplicate-slide",
      editTargets: [
        rwp("sh/6tovahoz", "slide title"),
        rw("sh/d4vmtwra", "Yakov Peysakhzon insight"),
        rwp("sh/sji5snel", "Alexey Bakhterov insight"),
        rwp("sh/6hcrmhk3", "Tatiana Kovalevskaya insight"),
        rw("sh/3ylc7u54", "Oleg Tembotov insight")
      ]
    },
    {
      outputSlide: 4, sourceSlide: 10, narrativeRole: "TV advertising implications",
      reuseMode: "duplicate-slide",
      editTargets: [
        rw("sh/9gr2p8nq", "slide title"),
        rw("sh/gvy90je9", "main thesis and conclusions")
      ]
    },
    {
      outputSlide: 5, sourceSlide: 11, narrativeRole: "final conclusions",
      reuseMode: "duplicate-slide",
      editTargets: [
        rw("sh/6tovahoz", "slide title"),
        rw("sh/d4vmtwra", "linear TV conclusion"),
        rw("sh/sji5snel", "digital TV and CTV conclusion"),
        rw("sh/6hcrmhk3", "data and AI conclusion"),
        rw("sh/3ylc7u54", "final market imperative")
      ]
    }
  ],
  omittedSourceSlides: [2,3,4,5,6,7,8,9].map(sourceSlide => ({
    sourceSlide, reason: "layout not required for the five-slide narrative"
  }))
};

await fs.writeFile(`${tmp}/template-frame-map.json`, JSON.stringify(map, null, 2), "utf8");
await fs.writeFile(`${tmp}/template-audit.txt`,
`Source deck: 11 slides, 1280x720. Dominant typography: Cera Pro/Cera Pro Black.
Palette: white, black, vivid orange (#ff4b00 family). Strong large headings and orange emphasis.
Reusable frames selected: slide 1 cover; slide 10 image/text split; slide 11 structured conclusions.
All output slides duplicate source slides and edit inherited objects only. Empty structural placeholders on source slide 1 are deleted.
The source deck image on the cover is preserved because it is thematically adjacent to media/TV and the official external image download was unavailable.
`, "utf8");
await fs.writeFile(`${tmp}/deviation-log.txt`,
`Slide 1: title rewritten; two empty body placeholders deleted; source visual retained.
Slides 2, 3, 5: source slide 11 copied; all five inherited text boxes rewritten without adding objects.
Slide 4: source slide 10 copied; title and body rewritten; inherited TV visual retained.
`, "utf8");
await fs.writeFile(`${tmp}/source-notes.txt`,
`Primary content: C:/Users/Roman/Downloads/Plan_prezy.docx
Visual template: C:/Users/Roman/Downloads/5_-_Novosti_aprel_2026_25_05_Ba9Cp2.pptx
Verification source: https://adindex.ru/news/marketing/2026/07/1/346747.phtml
Official event page: https://adindex.city/
`, "utf8");
