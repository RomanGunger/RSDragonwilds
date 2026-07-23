import unreal

MONTAGE_PATHS = [
    "/Game/Weapons/Montages/A_SW_Combo_Montage",
    "/Game/Weapons/Montages/A_SW_Attack_05_Montage",
]

TARGET_SLOT = "UpperBody"
AB_MQ_PATH = "/Game/GameplayAbilitySystem/Characters/AB_MQ"
AB_SWORD_PATH = "/Game/GameplayAbilitySystem/Characters/AB_Sword"
PARENT_CLASS_PATH = "/Script/RuneScapeDW.RSAnimInstance"


def log(msg: str) -> None:
    unreal.log(f"[FixSwordAttackAnim] {msg}")


def fix_montage_slot(asset_path: str, slot_name: str) -> bool:
    montage = unreal.load_asset(asset_path)
    if montage is None:
        unreal.log_error(f"Could not load montage: {asset_path}")
        return False

    before = unreal.AnimationLibrary.get_montage_slot_names(montage)
    log(f"{asset_path} slots before: {[str(s) for s in before]}")

    if not unreal.RSAnimBlueprintHelper.set_montage_slot_name(montage, unreal.Name(slot_name)):
        unreal.log_error(f"Failed to update montage slot: {asset_path}")
        return False

    unreal.EditorAssetLibrary.save_loaded_asset(montage)
    after = unreal.AnimationLibrary.get_montage_slot_names(montage)
    log(f"{asset_path} slots after: {[str(s) for s in after]}")
    return True


def reparent_ab_mq_to_rs_anim_instance() -> bool:
    ab_mq = unreal.load_asset(AB_MQ_PATH)
    if ab_mq is None:
        unreal.log_error(f"Could not load anim blueprint: {AB_MQ_PATH}")
        return False

    parent_class = unreal.load_class(None, PARENT_CLASS_PATH)
    if parent_class is None:
        unreal.log_error(f"Could not load parent class: {PARENT_CLASS_PATH}")
        return False

    if not unreal.RSAnimBlueprintHelper.reparent_anim_blueprint(ab_mq, parent_class):
        unreal.log_error("Failed to reparent AB_MQ")
        return False

    unreal.RSAnimBlueprintHelper.remove_blueprint_bool_variable(ab_mq, unreal.Name("bShouldSearch"))

    unreal.EditorAssetLibrary.save_loaded_asset(ab_mq)
    log(f"Reparented AB_MQ to {PARENT_CLASS_PATH}")

    ab_sword = unreal.load_asset(AB_SWORD_PATH)
    if ab_sword is not None:
        unreal.RSAnimBlueprintHelper.compile_anim_blueprint(ab_sword)
        unreal.EditorAssetLibrary.save_loaded_asset(ab_sword)
        log(f"Recompiled {AB_SWORD_PATH}")

    return True


def main() -> None:
    ok = True
    for montage_path in MONTAGE_PATHS:
        if unreal.EditorAssetLibrary.does_asset_exist(montage_path):
            ok = fix_montage_slot(montage_path, TARGET_SLOT) and ok
        else:
            log(f"Skipping missing montage: {montage_path}")

    ok = reparent_ab_mq_to_rs_anim_instance() and ok

    if ok:
        log("Done.")
    else:
        unreal.log_error("Completed with errors.")


if __name__ == "__main__":
    main()
