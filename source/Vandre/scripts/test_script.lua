function _init()
	local entityDefinitions = {
		CreateEntityDefinition("entityA", 0, 0, 0, 0),
		CreateEntityDefinition("entityB", 0, 0, 1, 0),
		CreateEntityDefinition("entityC", 0, 0, 0.75, 0),
		CreateEntityDefinition("entityD", 0, 0, 0, 16);
	}

	local testVolume = CreateStaticVolumeEntity("testVolume", 0, 10, 20, 20);
	RegisterCallback_OnVolumeEntered(testVolume, OnVolumeEntered);
	RegisterCallback_OnVolumeExited(testVolume, OnVolumeExited);

	for _, entityDef in pairs(entityDefinitions) do
		local entity = CreateDynamicEntity(entityDef.name, entityDef.pos.x, entityDef.pos.y, entityDef.vel.x, entityDef.vel.y);
		RegisterCallback_OnEntityDestroyed(entity, OnEntityDestroyed);
	end
end

function CreatePoint(x, y)
	return {
		x = x,
		y = y
	}
end

function CreateEntityDefinition(name, x, y, dx, dy)
	return {
		name = name,
		pos = CreatePoint(x, y),
		vel = CreatePoint(dx, dy),
	}
end

function OnEntityDestroyed(entity)
	print("Lua::OnEntityDestroyed - Entity id " .. entity .. " has been destroyed and is no longer valid.");
end

function OnVolumeEntered(volumeEntity, entity)
	print("Lua::OnVolumeEntered - " .. GetEntityName(entity) .. " has entered " .. GetEntityName(volumeEntity) .. ".")
end

function OnVolumeExited(volumeEntity, entity)
	print("Lua::OnVolumeExited - " .. GetEntityName(entity) .. " has exited " .. GetEntityName(volumeEntity) .. ". Registering it for destruction!")
	DestroyEntity(entity);
end