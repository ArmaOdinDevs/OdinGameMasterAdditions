/**
Entity Skill Attribute for getting and setting varriables in Editor Attribute window
*/
[BaseContainerProps(), SCR_BaseEditorAttributeCustomTitle()]
class ODIN_SkillEditorAttribute : SCR_BaseValueListEditorAttribute
{
	override SCR_BaseEditorAttributeVar ReadVariable(Managed item, SCR_AttributesManagerEditorComponent manager)
	{
		SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(item);
		if (!editableEntity)
			return null;
		
		IEntity owner =  editableEntity.GetOwner();
		if (!owner)
			return null;
		
		SCR_AIConfigComponent AIConfigComp = SCR_AIConfigComponent.Cast(owner.FindComponent(SCR_AIConfigComponent));
		if (!AIConfigComp)
			return null;
			
		return SCR_BaseEditorAttributeVar.CreateFloat(Math.Round(AIConfigComp.m_Skill * 100));
	}
	
	override void WriteVariable(Managed item, SCR_BaseEditorAttributeVar var, SCR_AttributesManagerEditorComponent manager, int playerID)
	{
		if (!var)
			return;
		
		SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(item);
		
		IEntity owner =  editableEntity.GetOwner();
		if (!owner)
			return;
		
		SCR_AIConfigComponent AIConfigComp = SCR_AIConfigComponent.Cast(owner.FindComponent(SCR_AIConfigComponent));
		if (!AIConfigComp)
			return;

		AIConfigComp.m_Skill = var.GetFloat() / 100;
		
		SCR_AIGroup group = SCR_AIGroup.Cast(owner);
		if (!group)
			return;
		
		array<AIAgent> agents = {};
		group.GetAgents(agents);
		foreach (AIAgent agent : agents)
		{
			IEntity entity = agent.GetControlledEntity();
			if (!entity)
				continue;
			
			SCR_AICombatComponent combatComponent = SCR_AICombatComponent.Cast(entity.FindComponent(SCR_AICombatComponent));
			if (!combatComponent)
				continue;
			
			combatComponent.SetAISkill(var.GetInt());
		};
	}
};